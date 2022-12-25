import { ParamsService } from './../params.service';
import { LandscapeService } from './../landscape.service';
import Point from 'src/LandscapeClasses/point';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Subject, firstValueFrom } from 'rxjs';

import { CanvasService } from './../canvas.service';
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

  redrawEvent: Subject<void> = new Subject<void>();
  cleanEvent: Subject<void> = new Subject<void>();

  private width = 960;
  private height = 540;
  private mult = 1;

  constructor(
    private router: Router,
    private canvas_service: CanvasService,
    //private params_service: ParamsService
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
        .then(res => this.canvases = res)
    }
    //this.params_service.get(1).subscribe(res => window.alert(res.mult));
  }

  ngOnInit() { }

  onCanvasSelect(list_elem: listElem) {
    this.selected_canvas_id = list_elem.id;
  }

  onLoad() {
    if (this.selected_canvas_id) {
      firstValueFrom(this.canvas_service.getCanvas(this.selected_canvas_id))
        .then(res => {
          LandscapeService.setCanvas(res)

          if (LandscapeService.hmp)
          {
            let c: Point = LandscapeService.hmp.map_points_center;
            LandscapeService.hmp.move(new Point(-c.x + (this.width / (2 * this.mult)), -c.y + (this.height / (2 * this.mult)), -c.z));

            /*firstValueFrom(this.params_service.get(this.selected_canvas_id!))
              .then(p => {
                window.alert(p.mult);
                LandscapeService.hmp!.scale(new Point(p.mult, p.mult, p.mult));
              })
              .catch(e => window.alert('Couldn\'t get params\n' + e.message))*/
          }

          this.redrawEvent.next();
        })
        .catch(e => window.alert(e.message))
    }
    else
      window.alert("Choose canvas first")
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

  onBack() {
    localStorage.removeItem('canvas_user_id');
    this.router.navigate(['/ModeratorWindow']);
  }
}

interface CanvasNameId {
  name: string;
  id: number;
}