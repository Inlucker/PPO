import { Params, ParamsService } from './../params.service';
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
  //canvas_name: string; //= 'Canvas Name';
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
    
  constructor(private user_service: UserService, private router: Router,
    private canvas_service: CanvasService, private params_service: ParamsService)
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
    
    this.updateCanvasesList();

    this.params = LandscapeService.params;
  }

  ngOnInit(): void { }
  
  private updateCanvasesList() {
    if (this.canvas_user_id) {
      firstValueFrom(this.canvas_service.getCanvasesByUserId(this.canvas_user_id))
      .then(res => {
        this.canvases = res;
      })
        .catch(e => {
          window.alert(e.message() + '\nRedirecting to /login');
          this.routeToLogin();
      })
    }
    else {
      window.alert('Couldn\'t get canvas_user_id' + '\nRedirecting to /login');
      this.routeToLogin();
    }
  }

  onCanvasSelect(list_elem: listElem) {
    this.selected_canvas_id = list_elem.id;
  }

  onSend()
  {
    if (LandscapeService.canvas && LandscapeService.hmp)
    {
      LandscapeService.canvas.heights_map_points = LandscapeService.hmp.toStr();
      //color
      LandscapeService.canvas.red = this.params.red;
      LandscapeService.canvas.green = this.params.green;
      LandscapeService.canvas.blue = this.params.blue;
      firstValueFrom(this.canvas_service.postCanvas(LandscapeService.canvas))
        .then(canvas_id =>
        {
          this.updateCanvasesList();
          this.params.canvas_id = canvas_id;
          firstValueFrom(this.params_service.post(this.params))
            .catch(e => window.alert('You couldn\'t create params\n' + e.message));
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert('No canvas to send');
  }

  onLoad() {
    if (this.selected_canvas_id) {
      firstValueFrom(this.canvas_service.getCanvas(this.selected_canvas_id))
        .then(res =>
        {
          firstValueFrom(this.params_service.get(this.selected_canvas_id!))
            .then(p =>
            {
              this.params.updateGetParams(p);
              LandscapeService.setCanvas(res)

              this.params.updateResolutionByStr();
              LandscapeService.updateResolution();
              this.changeResolutionEvent.next(new Resolution(this.params.resolution_str));
            })
            .catch(e =>
            {
              window.alert('couldn\'t load params\n' + e.message)
              LandscapeService.setCanvas(res)

              this.params.updateResolutionByStr();
              LandscapeService.updateResolution();
              this.changeResolutionEvent.next(new Resolution(this.params.resolution_str));
              //this.redrawEvent.next();
            })
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first")
  }

  onUpdate()
  {
    if (LandscapeService.canvas && this.selected_canvas_id && LandscapeService.hmp) {
      LandscapeService.canvas.heights_map_points = LandscapeService.hmp.toStr();
      LandscapeService.canvas.id = this.selected_canvas_id;
      LandscapeService.canvas.red = this.params.red;
      LandscapeService.canvas.green = this.params.green;
      LandscapeService.canvas.blue = this.params.blue;
      this.params.canvas_id = this.selected_canvas_id;
      firstValueFrom(this.canvas_service.updateCanvas(LandscapeService.canvas))
        .then(() =>
        {
          this.updateCanvasesList();
          firstValueFrom(this.params_service.put(this.params))
            .catch(e => window.alert('You couldn\'t update params\n' + e.message));
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first OR No canvas to send");
  }

  onDeleteCanvas() {
    if (this.selected_canvas_id)
    {
      firstValueFrom(this.canvas_service.delete(this.selected_canvas_id))
        .then(() => {
          this.updateCanvasesList()
          this.selected_canvas_id = undefined;
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first");
  }
  
  onGenerate() {
    firstValueFrom(this.canvas_service.generate(this.params))
      .then(c => {
        LandscapeService.setGenCanvas(c);
        this.redrawEvent.next();
      })
      .catch(e => window.alert(e.message));
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
    LandscapeService.updateResolution();
    this.changeResolutionEvent.next(new Resolution(this.params.resolution_str));
  }
  onChangeMult() {
    LandscapeService.updateMult(this.params.mult);
    this.redrawEvent.next();
  }
  onChangeSize() {
    if (localStorage.getItem('size')) {
      let old_s: number = +localStorage.getItem('size')!;
      if (this.params.size > old_s)
        this.params.size = (old_s - 1) * 2 + 1;
      else if (this.params.size < old_s)
        this.params.size = (old_s - 1) / 2 + 1;
      
      LandscapeService.updateSize(this.params.size);
      this.params.range = (this.params.size - 1) * 3 / 4;
    }
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
    this.redrawEvent.next();
  }
  onChangeCanvasName() {
    LandscapeService.updateCanvasName(this.params.canvas_name);
  }

  onExit() {
    firstValueFrom(this.user_service.logout())
      .then(() => localStorage.removeItem('logged'));
    this.routeToLogin();
  }
  
  onDelete() {
    firstValueFrom(this.user_service.delete())
      .then(() => localStorage.removeItem('logged'));
    this.routeToLogin();
  }

  private routeToLogin() {
    localStorage.removeItem('logged')
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