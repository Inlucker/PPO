import { NgFor } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { firstValueFrom } from 'rxjs';

import { CanvasService, Canvas } from './../canvas.service';
import { listElem } from './../list-item/list-item.component';

@Component({
  selector: 'app-moderator-canvas-window',
  templateUrl: './moderator-canvas-window.component.html',
  styleUrls: ['./moderator-canvas-window.component.css']
})
export class ModeratorCanvasWindowComponent implements OnInit {
  canvas_user_id: number | undefined = undefined;
  canvases: CanvasNameId[] = [];
  selected_canvas_id: number | undefined = undefined;
  cur_canvas: Canvas | undefined;

  constructor(
    private router: Router,
    private canvas_service: CanvasService
    ) {
    let r = localStorage.getItem('role');
    if (r == 'canvas_user')
      this.router.navigate(['/CanvasUserWindow']);
    if (!r)
      router.navigate(['/login'])

    localStorage.setItem('moderator_endpoint', '/ModeratorCanvasWindow');
    let cui: string | null = localStorage.getItem('canvas_user_id')
    if (cui)
      this.canvas_user_id = +cui;
    
    if (this.canvas_user_id) {
      firstValueFrom(canvas_service.getCanvasesByUserId(this.canvas_user_id))
        .then(res => {
          this.canvases = res;
          //this.canvases.forEach(val => {window.alert(val.name)})
        })
    }
  }

  ngOnInit() { }

  onCanvasSelect(list_elem: listElem) {
    this.selected_canvas_id = list_elem.id;
  }

  onLoad() {
    if (this.selected_canvas_id) {
      firstValueFrom(this.canvas_service.getCanvas(this.selected_canvas_id))
        .then(res => {
          this.cur_canvas = res;
          //window.alert(res.name + res.heights_map);
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first")
  }

  onBack() {
    localStorage.removeItem('canvas_user_id');
    this.router.navigate(['/ModeratorWindow']);
  }
}

interface CanvasNameId {
  name: string;
  id: number;
}