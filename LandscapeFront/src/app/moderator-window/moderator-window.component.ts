import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { firstValueFrom } from 'rxjs';

import { UserService, User } from '../user.service';
import { CanvasService, Canvas } from '../canvas.service';
import { listElem } from './../list-item/list-item.component';

@Component({
  selector: 'app-moderator-window',
  templateUrl: './moderator-window.component.html',
  styleUrls: ['./moderator-window.component.css']
})
export class ModeratorWindowComponent implements OnInit {
  free_users: UserName[] = [];
  users: UserName[] = [];
  selectedFreeUser: string | undefined = undefined;
  selectedUser: string | undefined = undefined;

  constructor(
    private user_service: UserService,
    private canvas_service: CanvasService,
    private router: Router,
    ) {
      let r = localStorage.getItem('role');
      if (r == 'canvas_user')
        this.router.navigate(['/CanvasUserWindow']);
      if (!r)
        router.navigate(['/login'])

      localStorage.setItem('moderator_endpoint', '/ModeratorWindow');
      localStorage.removeItem('canvas_user_id');
        
      user_service.getFreeUsers().subscribe(res => res.forEach(val => this.free_users.push({name: val})))
      user_service.getUsers().subscribe(res => res.forEach(val => this.users.push({name: val})))
  }

  onFreeUserSelect(list_elem: listElem) {
    this.selectedFreeUser = list_elem.name;
  }

  onUserSelect(list_elem: listElem) {
    this.selectedUser = list_elem.name;
  }

  ngOnInit() {
  }

  onWatch() {
    if (this.selectedUser) {
      firstValueFrom(this.user_service.getCanvasUserId(this.selectedUser))
        .then(res => {
          localStorage.setItem('canvas_user_id', res.toString())
          this.router.navigate(['/ModeratorCanvasWindow']);
        })
    }
    else
      window.alert("Choose user first");
  }

  onExit() {
    firstValueFrom(this.user_service.logout())
      .then(() => localStorage.removeItem('logged'));
    localStorage.removeItem('role');
    localStorage.removeItem('moderator_endpoint');
    this.router.navigate(['/login']);
  }
  
  onDeleteSelf() {
    firstValueFrom(this.user_service.delete())
      .then(() => localStorage.removeItem('logged'));
    localStorage.removeItem('role');
    localStorage.removeItem('moderator_endpoint');
    this.router.navigate(['/login']);
  }

  onAddUser() {
    if (this.selectedFreeUser)
      firstValueFrom(this.user_service.add(this.selectedFreeUser))
      .then(res => {
        this.user_service.getFreeUsers().subscribe(res => res.forEach(val => this.free_users.push({name: val})))
        this.user_service.getUsers().subscribe(res => res.forEach(val => this.users.push({name: val})))
      })
      .catch(e => window.alert(e.message));
    else
      window.alert("Choose free user first");
  }

  onDeleteUser() {
    if (this.selectedUser)
      firstValueFrom(this.user_service.remove(this.selectedUser))
      .then(res => {
        this.user_service.getFreeUsers().subscribe(res => res.forEach(val => this.free_users.push({name: val})))
        this.user_service.getUsers().subscribe(res => res.forEach(val => this.users.push({name: val})))
      })
      .catch(e => window.alert(e.message));
    else
      window.alert("Choose user first");
  }
}

interface UserName {
  name: string;
}