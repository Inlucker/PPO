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
    ) {
      let r = localStorage.getItem('role');
      if (!r)
        router.navigate(['/login'])
      if (r == 'moderator') {
        let url = localStorage.getItem('moderator_endpoint');
        if (url)
          this.router.navigate([url]);
        else
          this.router.navigate(['/ModeratorWindow']);
      }
    }

  ngOnInit(): void {}

  onExit() {
    this.user_service.logout().subscribe();
    localStorage.removeItem('role');
    this.router.navigate(['/']);
  }
  
  onDelete() {
    this.user_service.delete().subscribe();
    localStorage.removeItem('role');
    this.router.navigate(['/']);
  }
}
