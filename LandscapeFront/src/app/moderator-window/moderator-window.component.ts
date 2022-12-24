import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { firstValueFrom } from 'rxjs';

import { UserService, User } from '../user.service';

@Component({
  selector: 'app-moderator-window',
  templateUrl: './moderator-window.component.html',
  styleUrls: ['./moderator-window.component.css']
})
export class ModeratorWindowComponent implements OnInit {
  free_users: string[] = [];
  users: string[] = [];
  selectedFreeUser: string | undefined = undefined;
  selectedUser: string | undefined = undefined;

  constructor(
    private user_service: UserService,
    private router: Router
    ) {
      let r = localStorage.getItem('role');
      if (r == 'canvas_user')
        this.router.navigate(['/CanvasUserWindow']);
      if (!r)
        router.navigate(['/login'])

      localStorage.setItem('moderator_endpoint', '/ModeratorWindow');
        
      user_service.getFreeUsers().subscribe(res => this.free_users = res)
      user_service.getUsers().subscribe(res => this.users = res)
  }

  onFreeUserSelect(name: string) {
    this.selectedFreeUser = name;
  }

  onUserSelect(name: string) {
    this.selectedUser = name;
  }

  ngOnInit() {
  }

  onWatch() {
    this.router.navigate(['/ModeratorCanvasWindow']);
  }

  onExit() {
    this.user_service.logout().subscribe();
    localStorage.removeItem('role');
    localStorage.removeItem('moderator_endpoint');
    this.router.navigate(['/']);
  }
  
  onDeleteSelf() {
    this.user_service.delete().subscribe();
    localStorage.removeItem('role');
    localStorage.removeItem('moderator_endpoint');
    this.router.navigate(['/']);
  }

  onAddUser() {
    if (this.selectedFreeUser)
      firstValueFrom(this.user_service.add(this.selectedFreeUser))
      .then(res => {
        this.user_service.getFreeUsers().subscribe(res => this.free_users = res);
        this.user_service.getUsers().subscribe(res => this.users = res);
      })
      .catch(e => window.alert(e.message));
  }

  onDeleteUser() {
    if (this.selectedUser)
      firstValueFrom(this.user_service.remove(this.selectedUser))
      .then(res => {
        this.user_service.getFreeUsers().subscribe(res => this.free_users = res);
        this.user_service.getUsers().subscribe(res => this.users = res);
      })
      .catch(e => window.alert(e.message));
  }
}
