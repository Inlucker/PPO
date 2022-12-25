import Point from 'src/LandscapeClasses/point';
import { listElem } from './../list-item/list-item.component';
import { firstValueFrom, Subject } from 'rxjs';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { UserService } from '../user.service';
import { CanvasService, Canvas } from './../canvas.service';

@Component({
  selector: 'app-canvas-user-window',
  templateUrl: './canvas-user-window.component.html',
  styleUrls: ['./canvas-user-window.component.css']
})
export class CanvasUserWindowComponent implements OnInit {
  canvas_name: string = 'Canvas Name';
  resolution: string = '960x540';
  draw_type: string = 'ZBuffer';
  canvas_user_id: number | undefined = undefined; 
  canvases: CanvasNameId[] = [];  
  selected_canvas_id: number | undefined = undefined; 
  cur_canvas: Canvas | undefined;

  moveEvent: Subject<Point> = new Subject<Point>();
  scaleEvent: Subject<Point> = new Subject<Point>();
  rotateEvent: Subject<Point> = new Subject<Point>();
    
  constructor(private user_service: UserService, private router: Router, private canvas_service: CanvasService)
  {
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
    
    let cui: string | null = localStorage.getItem('cur_user_id')
    if (cui)
      this.canvas_user_id = +cui;
  
    if (this.canvas_user_id) {
      firstValueFrom(canvas_service.getCanvasesByUserId(this.canvas_user_id))
      .then(res => {
        this.canvases = res;
      })
    }
  }

  ngOnInit(): void {}

  onCanvasSelect(list_elem: listElem) {
    this.selected_canvas_id = list_elem.id;
  }

  onLoad() {
    if (this.selected_canvas_id) {
      firstValueFrom(this.canvas_service.getCanvas(this.selected_canvas_id))
      .then(res => {
        this.cur_canvas = res;
      })
      .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first")
  }

  onMove(p: Point) {
    this.moveEvent.next(p);
  }
  onScale(p: Point) {
    this.scaleEvent.next(p);
  }
  onRotate(p: Point) {
    this.rotateEvent.next(p);
  }

  onExit() {
    this.user_service.logout().subscribe();
    localStorage.removeItem('role');
    localStorage.removeItem('cur_user_id');
    this.router.navigate(['/login']);
  }
  
  onDelete() {
    this.user_service.delete().subscribe();
    localStorage.removeItem('role');
    localStorage.removeItem('cur_user_id');
    this.router.navigate(['/login']);
  }
}

interface CanvasNameId {
  name: string;
  id: number;
}