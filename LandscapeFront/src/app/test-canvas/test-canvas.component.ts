import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';

@Component({
  selector: 'app-test-canvas',
  templateUrl: './test-canvas.component.html',
  styleUrls: ['./test-canvas.component.css']
})
export class TestCanvasComponent implements OnInit {
  @ViewChild('canvas', { static: true })
  canvas: ElementRef<HTMLCanvasElement> | undefined;  

  private ctx: CanvasRenderingContext2D | undefined;

  constructor() {
    
  }

  ngOnInit(): void {
    this.ctx = this.canvas!.nativeElement.getContext('2d')!;
  }

  plot(x: number, y: number, c: string = 'green', m: number = 1) {
    if (this.ctx) {
      this.ctx.fillStyle = c;
      this.ctx.fillRect(x, y, m, m);
    }
  }

  animate() {
    if (this.ctx) {
      this.ctx.fillStyle = 'red';
      const square = new Square(this.ctx);
      square.draw(5, 1, 20);
      this.plot(4, 10, 'green', 20)
    }
  }
}

export class Square {
  constructor(private ctx: CanvasRenderingContext2D) {}

  draw(x: number, y: number, z: number) {
    this.ctx.fillRect(z * x, z * y, z, z);
  }
}

/*import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';

@Component({
  selector: 'app-test-canvas',
  templateUrl: './test-canvas.component.html',
  styleUrls: ['./test-canvas.component.css']
})
export class TestCanvasComponent implements AfterViewInit {
  // its important myCanvas matches the variable name in the template
  @ViewChild('myCanvas')
  myCanvas: ElementRef<HTMLCanvasElement> | undefined;

  public context: CanvasRenderingContext2D | undefined;

  ngAfterViewInit(): void {
    this.context = this.myCanvas!.nativeElement.getContext('2d')!;
  }
}*/
