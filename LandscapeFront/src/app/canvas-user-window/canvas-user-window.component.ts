import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { UserService } from '../user.service';

@Component({
  selector: 'app-canvas-user-window',
  templateUrl: './canvas-user-window.component.html',
  styleUrls: ['./canvas-user-window.component.css']
})
export class CanvasUserWindowComponent implements OnInit {
  canvas_name: string = 'Canvas Name';
  resolution: string = '960x540';
  draw_type: string = 'ZBuffer';

  constructor(
    private user_service: UserService,
    private router: Router
    ) { }

  ngOnInit(): void {}

  onExit() {
    this.user_service.logout().subscribe();
    this.router.navigate(['/']);
  }
  
  onDelete() {
    this.user_service.delete().subscribe();
    this.router.navigate(['/']);
  }
}
