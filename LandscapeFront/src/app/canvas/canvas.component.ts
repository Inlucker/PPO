import { Params } from './../params.service';
import { ZBuffer } from './../../LandscapeClasses/zbuffer';
import { LandscapeService } from './../landscape.service';
import { Observable, Subscription } from 'rxjs';
import { Component, ViewChild, ElementRef, OnInit} from '@angular/core';
import { Input } from '@angular/core';

//export type Int = number & { __int__: void };

import TriPolArray from 'src/LandscapeClasses/tri-pol-array';
import Point from 'src/LandscapeClasses/point';

@Component({
  selector: 'app-canvas',
  templateUrl: './canvas.component.html',
  styleUrls: ['./canvas.component.css']
})
export class CanvasComponent implements OnInit {
  @Input() width: string = "981px";
  @Input() height: string = "561px";
  private resol: Resolution = { width: 960, height: 540 };
  res_width_str: string = '960px';
  res_height_str: string = '540px';
  
  @Input()
  set resolution(res: Resolution | undefined) {
    if (res)
    {
      this.resol = res;
      this.res_width_str =  this.resol.width + 'px';
      this.res_height_str = this.resol.height + 'px';
    }
  }

  @ViewChild('canvas', { static: true })
  canvas: ElementRef<HTMLCanvasElement> | undefined;  
  private ctx: CanvasRenderingContext2D | undefined;

  private eventsSubscription: Subscription = new Subscription();
  @Input() redrawEvent: Observable<void> = new Observable<void>();
  @Input() cleanEvents: Observable<void> = new Observable<void>();
  @Input() changeResolutionEvents: Observable<Resolution> = new Observable<Resolution>();

  private lkm_pressed: boolean = false;
  private pkm_pressed: boolean = false;
  private prev_x: number = -1;
  private prev_y: number = -1;

  constructor() { }

  ngOnInit(): void {
    this.eventsSubscription = this.redrawEvent.subscribe(() => this.animate());
    this.eventsSubscription = this.cleanEvents.subscribe(() => this.clearCanvas());
    this.eventsSubscription = this.changeResolutionEvents.subscribe((resol: Resolution) => this.changeResolution(resol));

    this.ctx = this.canvas!.nativeElement.getContext('2d')!;
    
    var c = document.getElementsByTagName('canvas')[0];
    c.width  = this.resol.width;
    c.height = this.resol.height;
    /*c.style.width  = this.width;
    c.style.height = this.height;*/
    this.animate();
  }

  ngOnDestroy() {
    this.eventsSubscription.unsubscribe();
  }

  changeResolution(resol: Resolution) {
    this.resol = resol;
    this.res_width_str = this.resol.width + 'px';
    this.res_height_str = this.resol.height + 'px';
    var can = document.getElementsByTagName('canvas')[0];
    can.width  = resol.width;
    can.height = resol.height;

    this.animate();
  }

  plot(x: number, y: number, c: string = 'green', m: number = 1) {
    if (this.ctx) {
      this.ctx.fillStyle = c;
      this.ctx.fillRect(x, y, m, m);
    }
  }

  drawLine(x1: number, y1: number, x2: number, y2: number, c: string = 'black') {
    if (this.ctx) {
      this.ctx.beginPath();
      this.ctx.strokeStyle = c;
      this.ctx.moveTo(x1, y1);
      this.ctx.lineTo(x2, y2);
      this.ctx.stroke();
    }
  }
  
  onMouseDown(event: any) {
    console.log(event, event.which);
    switch (event.which)
    {
      case 1:
        this.lkm_pressed = true;
        break;
      case 3:
        this.pkm_pressed = true;
        break;
    }
    this.prev_x = event.clientX;
    this.prev_y = event.clientY;
  }

  onMouseUp(event: any) {
    switch (event.which)
    {
      case 1:
        this.lkm_pressed = false;
        break;
      case 3:
        this.pkm_pressed = false;
        break;
    }
  }

  onMouseMove(event: any) {
    let speed = 1.3;
    let dx = (event.clientX - this.prev_x) / speed;
    let dy = (event.clientY - this.prev_y) / speed;
    this.prev_x = event.clientX;
    this.prev_y = event.clientY;

    if (this.lkm_pressed) {
      LandscapeService.rotate(new Point(dy, dx))
      this.animate();
    }
    if (this.pkm_pressed) {
      LandscapeService.move(new Point(dx, dy))
      this.animate();
    }
  }

  onMouseWheel(event: any) {
    //console.log(event, event.which);
    let speed = 10;
    let tmp = event.wheelDelta / 120;
    let ky = 1 - tmp / speed;
    console.log(ky);
    LandscapeService.scale(new Point(ky, ky, ky))
    this.animate();
  }

  animate() {
    let mult: number = LandscapeService.params.mult;
    var c = document.getElementsByTagName('canvas')[0];
    c.width = this.resol.width / mult;
    c.height = this.resol.height / mult;

    let draw_type = localStorage.getItem('draw_type');
    if (draw_type == 'ZBuffer')
    {
      let tpa = LandscapeService.tpa;
      tpa.update();
      let r = tpa.red;
      let g = tpa.green;
      let b = tpa.blue;
      //let color_hex = Params.rgbToHex(r, g , b);
      let zbuffer: ZBuffer = new ZBuffer();
      let height = this.resol.width / mult;
      let width = this.resol.height / mult;
      zbuffer.setSize(width, height);
      tpa.data.forEach(elem => {
        for (let i = Math.round(Math.max(elem.min_x!, 0.)); i < Math.round(Math.min(elem.max_x!, height)); i++) {
          for (let j = Math.round(Math.max(elem.min_y!, 0.)); j < Math.round(Math.min(elem.max_y!, width)); j++) {
            if (elem.isInTriangle(i, j)) {
              if (zbuffer.data[i][j] < elem.getZ(i, j)) {
                zbuffer.data[i][j] = elem.getZ(i, j);
                let inten = elem.intensity;
                let color_rgb_style = Params.rgbToStyle(r * inten, g * inten, b * inten);
                this.plot(i, j, color_rgb_style);
              }
            }
          }
        }
        /*for (let i: Int = Math.round(Math.max(elem.min_x!, 0.)) as Int; i < (Math.round(Math.min(elem.max_x!, height)) as Int); i++) {
          for (let j: Int = Math.round(Math.max(elem.min_y!, 0.)) as Int; j < (Math.round(Math.min(elem.max_y!, width)) as Int); j++) {
            if (elem.isInTriangle(i, j)) {
              if (zbuffer.data[i][j] < elem.getZ(i, j)) {
                zbuffer.data[i][j] = elem.getZ(i, j);
                let inten = elem.intensity;
                let color_rgb_style = Params.rgbToStyle(r * inten, g * inten, b * inten);
                this.plot(i, j, color_rgb_style);
                //(* frame_buffer)(i, j) = QColor(round(red * intensivity), round(green * intensivity), round(blue * intensivity));
              }
            }
          }
        }*/
      });
    }
    else
    {
      if (this.ctx) {
        this.clearCanvas();

        let counter: number = 0;
        
        let style: string = this.rgbToStyle(LandscapeService.tpa.red, LandscapeService.tpa.green, LandscapeService.tpa.blue);
        LandscapeService.tpa.data.forEach(tp => {
          counter++;
          this.drawLine(tp.p1.x, tp.p1.y, tp.p2.x, tp.p2.y, style);
          this.drawLine(tp.p2.x, tp.p2.y, tp.p3.x, tp.p3.y, style);
          this.drawLine(tp.p3.x, tp.p3.y, tp.p1.x, tp.p1.y, style);
        })
        //this.plot(4, 10, 'green', 20)
        //this.plot(50, 100, 'green', 10)
      }
    }
  }

  clearCanvas() {
    if (this.ctx) {
      this.ctx.clearRect(0, 0, this.resol.width, this.resol.height);
    }
  }

  private rgbToStyle(r: number, g: number, b: number): string {
    return 'rgb(' + r + ',' + g + ',' + b + ')';
  }
}

export class Resolution {
  constructor(res: string) {
    this.width = +res.substring(0, res.indexOf('x'));
    this.height = +res.substring(res.indexOf('x') + 1, res.length);
  }
  width: number = 0;
  height: number = 0;
}