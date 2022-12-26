import TriangularPolygon from './triangular-polygon'

export default class TriPolArray {
  data: TriangularPolygon[] = [];
  elems_num: number = 0;
  red: number = 0;
  green: number = 0;
  blue: number = 0;

  constructor(new_size?: number, new_r?: number, new_g?: number, new_b?: number) {
    this.elems_num = new_size ?? 0;
    /*for (let i: number = 0; i < this.elems_num; i++) {
      this.data.push(new TriangularPolygon(new Point(), new Point(), new Point()));
    }*/
    this.red = new_r ?? 0;
    this.green = new_g ?? 0;
    this.blue = new_b ?? 0;
  }

  update() {
    this.data.forEach(el => el.udpate());
  }

  setColor(c: Color) {
    if (c) {
      this.red = c.r;
      this.green = c.g;
      this.blue = c.b;
    }
  }

  getStr(): string {
    let res: string = '';
    this.data.forEach(tp => { res += tp.getStr() + '\n'} )
    return res;
  }

  print() {
    window.alert(this.getStr());
  }
}

interface Color {
  r: number;
  g: number;
  b: number;
}