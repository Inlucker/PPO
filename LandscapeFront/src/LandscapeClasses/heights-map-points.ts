import Point from './point';
import TriPolArray from './tri-pol-array';
import TriangularPolygon from './triangular-polygon';

export default class HeightsMapPoints {
  points: Point[][] = [];
  width: number = 0;
  height: number = 0;
  elems_num: number = 0;
  map_points_center: Point = new Point();

  constructor(hmp: string)
  {
    var i: number = 0;
    var x: string = '', y: string = '', z: string = '';

    while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
    {
      x += hmp[i];
      i++;
    }
    this.width = +x;
    i++;
    x = '';

    while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
    {
      x += hmp[i];
      i++;
    }
    this.height = +x;
    i++;
    x = '';

    this.elems_num = this.width*this.height;
    
    var j: number = 0;
    var k: number = 0;
    for (j = 0; j < this.height; j++) {
      var tmp_arr: Point[] = [];
      for (k = 0; k < this.width; k++) {
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            x += hmp[i];
            i++;
        }
        i++;
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            y += hmp[i];
            i++;
        }
        i++;
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            z += hmp[i];
            i++;
        }
        i++;
        tmp_arr.push(new Point(+x, +y, +z))
        x = '', y = '', z = '';
      }
      this.points.push(tmp_arr)
    }
    this.updateCenter();
  }

  createTriPolArray(r?: number, g?: number, b?: number): TriPolArray
  {
    var new_tri_pol_mas: TriPolArray = new TriPolArray((this.width - 1) * 2 * (this.height - 1), r, g, b);
    
    var tpa_i: number = 0;
    
    for (let i: number = 0; i < (this.height-1); i++)
    {
      for (let j: number = 0; j < (this.width-1); j++)
      {
        if ((j+i) % 2 == 1)
        {
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i][j+1], this.points[i+1][j]);
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i+1][j], this.points[i][j+1], this.points[i+1][j+1]);
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i][j + 1], this.points[i + 1][j]));
          tpa_i++;
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i+1][j], this.points[i][j+1], this.points[i+1][j+1]));
          tpa_i++;
        }
        else
        {
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i+1][j+1], this.points[i][j+1]);
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i+1][j], this.points[i+1][j+1]);
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i+1][j+1], this.points[i][j+1]));
          tpa_i++;
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i+1][j], this.points[i+1][j+1]));
          tpa_i++;
        }
      }
    }

    return new_tri_pol_mas;
  }

  transform(move: Point, scale: Point, rotate: Point) {
    this.points.forEach(point_arr =>
      point_arr.forEach(point => {
        point.transform(move, scale, rotate, this.map_points_center);
      }))
    this.updateCenter();
  }

  move(move: Point) {
    this.points.forEach(point_arr =>
      point_arr.forEach(point => {
        point.move(move);
      }))
    this.updateCenter();
  }
  
  scale(scale: Point) {
    this.points.forEach(point_arr =>
      point_arr.forEach(point => {
        point.scale(scale, this.map_points_center);
      }))
    this.updateCenter();
  }

  rotate(rotate: Point) {
    this.points.forEach(point_arr =>
      point_arr.forEach(point => {
        point.rotate(rotate, this.map_points_center);
      }))
    this.updateCenter();
  }

  getStr(): string {
    let res: string = '';
    this.points.forEach(arr => arr.forEach(val => res += val.getStr() + '\n'))
    return res;
  }

  print() {
    window.alert(this.getStr());
  }

  private updateCenter() {
    let i: number = 0;
    let rez: Point = new Point();

    this.points.forEach(point_arr => {
      point_arr.forEach(point => {
        rez.x = (rez.x + point.x);
        rez.y = (rez.y + point.y);
        rez.z = (rez.z + point.z);
        i++;
      })
    })
    this.map_points_center = new Point(rez.x/i, rez.y/i, rez.z/i);
  }
}
  
  
  