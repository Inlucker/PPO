import { Component, OnInit } from '@angular/core';

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

  constructor() { }

  ngOnInit() {
  }

}
