import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { UserService, User } from '../user.service';

@Component({
  selector: 'app-moderator-window',
  templateUrl: './moderator-window.component.html',
  styleUrls: ['./moderator-window.component.css']
})
export class ModeratorWindowComponent implements OnInit {

  constructor(
    private user_service: UserService,
    private router: Router
    ) { }

  ngOnInit() {
  }

  onWatch() {
    this.router.navigate(['/ModeratorCanvasWindow']);
  }

  onExit() {
    this.user_service.logout().subscribe();
    this.router.navigate(['/']);
  }
  
  onDelete() {
    this.user_service.delete().subscribe();
    this.router.navigate(['/']);
  }
}
