import { Params } from './../params.service';
import { Resolution } from './../canvas/canvas.component';
import Point from 'src/LandscapeClasses/point';
import { listElem } from './../list-item/list-item.component';
import { firstValueFrom, Subject } from 'rxjs';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { UserService } from '../user.service';
import { CanvasService, Canvas } from './../canvas.service';
import { LandscapeService } from '../landscape.service';
import { ColorPickerModule } from 'ngx-color-picker';

@Component({
  selector: 'app-canvas-user-window',
  templateUrl: './canvas-user-window.component.html',
  styleUrls: ['./canvas-user-window.component.css']
})
export class CanvasUserWindowComponent implements OnInit {
  canvas_name: string = 'Canvas Name';
  //resolution_str: string = '960x540';
  //resolution: Resolution = new Resolution(this.resolution_str);
  params: Params;
  draw_type: string = 'ZBuffer';
  canvas_user_id: number | undefined = undefined; 
  canvases: CanvasNameId[] = [];  
  selected_canvas_id: number | undefined = undefined;

  redrawEvent: Subject<void> = new Subject<void>();
  cleanEvent: Subject<void> = new Subject<void>();
  changeResolutionEvent: Subject<Resolution> = new Subject<Resolution>();
    
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

    //this.resolution = new Resolution(this.resolution_str);
    this.params = LandscapeService.params;
    
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
          LandscapeService.setCanvas(res)
          this.redrawEvent.next();
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first")
  }
  
  onGenerate() {
    
  }

  onMove(p: Point) {
    LandscapeService.move(p);
    this.redrawEvent.next();
  }
  onScale(p: Point) {
    LandscapeService.scale(p);
    this.redrawEvent.next();
  }
  onRotate(p: Point) {
    LandscapeService.rotate(p);
    this.redrawEvent.next();
  }
  onClean() {
    this.cleanEvent.next();
  }
  onChangeResolution() {
    this.params.updateResolutionByStr();
    LandscapeService.updateResolution(new Resolution(this.params.resolution_str));
    this.changeResolutionEvent.next(new Resolution(this.params.resolution_str));
  }
  onChangeMult() {
    LandscapeService.updateMult(this.params.mult);
  }
  onChangeSize() {
    LandscapeService.updateSize(this.params.size);
  }
  onChangeRange() {
    LandscapeService.updateRange(this.params.range);
  }
  onChangeSmooth() {
    this.params.smooth = !this.params.smooth;
    LandscapeService.updateSmooth(this.params.smooth);
  }
  onChangeColor() {
    LandscapeService.updateColor(this.params.color_hex);
  }

  onExit() {
    firstValueFrom(this.user_service.logout())
      .then(() => localStorage.removeItem('logged'));
    LandscapeService.reset();
    localStorage.removeItem('role');
    localStorage.removeItem('cur_user_id');
    this.router.navigate(['/login']);
  }
  
  onDelete() {
    firstValueFrom(this.user_service.delete())
      .then(() => localStorage.removeItem('logged'));
    LandscapeService.reset();
    localStorage.removeItem('role');
    localStorage.removeItem('cur_user_id');
    this.router.navigate(['/login']);
  }
}

interface CanvasNameId {
  name: string;
  id: number;
}