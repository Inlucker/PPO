import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-moderator-canvas-window',
  templateUrl: './moderator-canvas-window.component.html',
  styleUrls: ['./moderator-canvas-window.component.css']
})
export class ModeratorCanvasWindowComponent implements OnInit {

  constructor(private router: Router) {
    let r = localStorage.getItem('role');
    if (r == 'canvas_user')
      this.router.navigate(['/CanvasUserWindow']);
    if (!r)
      router.navigate(['/login'])

    localStorage.setItem('moderator_endpoint', '/ModeratorCanvasWindow');
  }

  ngOnInit() { }

  onBack() {
    this.router.navigate(['/ModeratorWindow']);
  }
}
