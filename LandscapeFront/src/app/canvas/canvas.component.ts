import Point from 'src/LandscapeClasses/point';
import { Observable, Subscription } from 'rxjs';
import { Component, ViewChild, ElementRef, OnInit} from '@angular/core';
import { Input } from '@angular/core';

import { Canvas } from './../canvas.service';
import TriPolArray from 'src/LandscapeClasses/tri-pol-array';
import HeightsMapPoints from 'src/LandscapeClasses/heights-map-points';

@Component({
  selector: 'app-canvas',
  templateUrl: './canvas.component.html',
  styleUrls: ['./canvas.component.css']
})
export class CanvasComponent implements OnInit {
  @Input() width: number = 981;
  @Input() height: number = 561;
  width_str: string = this.width + 'px';
  height_str: string = this.height + 'px';
  private landscape: Canvas | undefined;
  @Input()
  set _canvas(val: Canvas | undefined) {
    if (val) {
      this.landscape = val;
      
      this.hmp = new HeightsMapPoints(this.landscape?.heights_map_points!);
      this.tpa = this.hmp.createTriPolArray(val?.red, val?.green, val?.blue);
      this.animate();
    }
  }

  //hmp: HeightsMapPoints = new HeightsMapPoints();
  private tpa: TriPolArray = new TriPolArray();
  private hmp: HeightsMapPoints | undefined;

  @ViewChild('canvas', { static: true })
  canvas: ElementRef<HTMLCanvasElement> | undefined;  
  private ctx: CanvasRenderingContext2D | undefined;

  private eventsSubscription: Subscription = new Subscription();
  @Input() moveEvents: Observable<Point> = new Observable<Point>();
  @Input() scaleEvents: Observable<Point> = new Observable<Point>();
  @Input() rotateEvents: Observable<Point> = new Observable<Point>();

  constructor() { }

  ngOnInit(): void {
    this.eventsSubscription = this.moveEvents.subscribe((p: Point) => this.move(p));
    this.eventsSubscription = this.scaleEvents.subscribe((p: Point) => this.scale(p));
    this.eventsSubscription = this.rotateEvents.subscribe((p: Point) => this.rotate(p));

    this.ctx = this.canvas!.nativeElement.getContext('2d')!;
    
    var c = document.getElementsByTagName('canvas')[0];
    c.width  = this.width;
    c.height = this.height;
    /*c.style.width  = this.width;
    c.style.height = this.height;*/
  }

  ngOnDestroy() {
    this.eventsSubscription.unsubscribe();
  }

  move(p: Point) {
    this.hmp?.move(p);
    this.tpa = this.hmp?.createTriPolArray(this.landscape?.red, this.landscape?.green, this.landscape?.blue)!;
    this.animate();
    //window.alert('move ' + p.getStr());
  }
  scale(p: Point) {
    this.hmp?.scale(p);
    this.tpa = this.hmp?.createTriPolArray(this.landscape?.red, this.landscape?.green, this.landscape?.blue)!;
    this.animate();
    //window.alert('scale ' + p.getStr());
  }
  rotate(p: Point) {
    this.hmp?.rotate(p);
    this.tpa = this.hmp?.createTriPolArray(this.landscape?.red, this.landscape?.green, this.landscape?.blue)!;
    this.animate();
    //window.alert('rotate ' + p.getStr());
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
      
      let style: string = this.rgbToStyle(this.tpa.red, this.tpa.green, this.tpa.blue);
      this.tpa.data.forEach(tp => {
        counter++;
        this.drawLine(tp.p1.x, tp.p1.y, tp.p2.x, tp.p2.y, style);
        this.drawLine(tp.p2.x, tp.p2.y, tp.p3.x, tp.p3.y, style);
        this.drawLine(tp.p3.x, tp.p3.y, tp.p1.x, tp.p1.y, style);
      })
      //window.alert(this.canvas?.nativeElement.toDataURL());
      //this.plot(4, 10, 'green', 20)
      //this.plot(50, 100, 'green', 10)
    }
  }

  clearCanvas() {
    if (this.ctx) {
      this.ctx.clearRect(0, 0, this.width, this.height);
      //this.ctx = this.canvas!.nativeElement.getContext('2d')!;
    }
  }

  private rgbToStyle(r: number, g: number, b: number): string {
    return 'rgb(' + r + ',' + g + ',' + b + ')';
  }
}


