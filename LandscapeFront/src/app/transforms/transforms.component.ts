import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import Point from 'src/LandscapeClasses/point';

@Component({
  selector: 'app-transforms',
  templateUrl: './transforms.component.html',
  styleUrls: ['./transforms.component.css']
})
export class TransformsComponent implements OnInit {
  moveX: number = 10;
  moveY: number = 10;
  moveZ: number = 10;
  
  scaleX: number = 0.9;
  scaleY: number = 1.0;
  scaleZ: number = 1.1;

  rotateX: number = 0;
  rotateY: number = 0;
  rotateZ: number = 10;

  @Output() move = new EventEmitter<Point>();
  @Output() scale = new EventEmitter<Point>();
  @Output() rotate = new EventEmitter<Point>();

  constructor() { }

  ngOnInit() { }

  onMove() {
    this.move.emit(new Point(this.moveX, this.moveY, this.moveZ));
  }

  onScale() {
    this.scale.emit(new Point(this.scaleX, this.scaleY, this.scaleZ));
  }

  onRotate() {
    this.rotate.emit(new Point(this.rotateX, this.rotateY, this.rotateZ));
  }
}
