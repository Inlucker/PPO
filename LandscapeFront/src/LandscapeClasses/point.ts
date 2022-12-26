export default class Point {
  x: number = 0;
  y: number = 0;
  z: number = 0;

  constructor(_x?: number, _y?: number, _z?: number) {
    this.x = _x ?? 0;
    this.y = _y ?? 0;
    this.z = _z ?? 0;
  }

  transform(move: Point, scale: Point, rotate: Point, center: Point) {
    this.move(move);
    this.scale(scale, center);
    this.rotate(rotate, center);
  }

  move(move: Point) {
    this.x += +move.x;
    this.y += +move.y;
    this.z += +move.z;
  }

  scale(scale: Point, center: Point) {
    let kx: number = +scale.x;
    let ky: number = +scale.y;
    let kz: number = +scale.z;
    let xc: number = +center.x;
    let yc: number = +center.y;
    let zc: number = +center.z;
    this.x = kx * this.x + xc * (1 - kx);
    this.y = ky * this.y + yc * (1 - ky);
    this.z = kz * this.z + zc * (1 - kz);
  }

  rotate(rotate: Point, center: Point) {
    this.rotateX(+rotate.x, center);
    this.rotateY(+rotate.y, center);
    this.rotateZ(+rotate.z, center);
  }

  rotateX(angle: number, center: Point) {
    //let xc: number = center.x;
    let yc: number = center.y;
    let zc: number = center.z;
    let radians: number = angle * Math.PI / 180;
    let tmp_y: number = this.y;
    let tmp_z: number = this.z;
    this.y = yc + (tmp_y - yc) * Math.cos(radians) + (tmp_z - zc) * Math.sin(radians);
    this.z = zc - (tmp_y - yc) * Math.sin(radians) + (tmp_z - zc) * Math.cos(radians);
  }

  rotateY(angle: number, center: Point) {
    let xc: number = center.x;
    //let yc: number = center.y;
    let zc: number = center.z;
    let radians: number = angle * Math.PI / 180;
    let tmp_x = this.x;
    let tmp_z = this.z;
    this.x = xc + (tmp_x - xc) * Math.cos(radians) + (tmp_z - zc) * Math.sin(radians);
    this.z = zc - (tmp_x - xc) * Math.sin(radians) + (tmp_z - zc) * Math.cos(radians);
  }

  rotateZ(angle: number, center: Point) {
    let xc: number = center.x;
    let yc: number = center.y;
    //let zc: number = center.z;
    let radians: number = angle * Math.PI / 180;
    let tmp_x = this.x;
    let tmp_y = this.y;
    this.x = xc + (tmp_x - xc) * Math.cos(radians) - (tmp_y - yc) * Math.sin(radians);
    this.y = yc + (tmp_x - xc) * Math.sin(radians) + (tmp_y - yc) * Math.cos(radians);
  }

  getStr(): string {
    let res: string = '';
    res = '(' + this.x + '; ' + this.y + '; ' + this.z + ')';
    return res;
  }
}
  