import { LandscapeService } from './../landscape.service';
import { Observable, Subscription } from 'rxjs';
import { Component, ViewChild, ElementRef, OnInit} from '@angular/core';
import { Input } from '@angular/core';

import TriPolArray from 'src/LandscapeClasses/tri-pol-array';

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

  drawTriPolArray(tpa: TriPolArray) {

  }

  animate() {
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