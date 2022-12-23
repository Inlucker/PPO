import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-moderator-canvas-window',
  templateUrl: './moderator-canvas-window.component.html',
  styleUrls: ['./moderator-canvas-window.component.css']
})
export class ModeratorCanvasWindowComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit() { }

  onBack() {
    this.router.navigate(['/ModeratorWindow']);
  }
}
