export class HeightsMap {
  data: number[][] = [];
  width: number = 0;
  height: number = 0;
  elems_num: number = 0;
  max_height: number = 0;

  constructor(hm: string) {
    let i: number = 0;
    let tmp = "";
    while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0') {
        tmp += hm[i];
        i++;
    }
    this.width = +tmp;
    i++;
    tmp = "";

    while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0') {
        tmp += hm[i];
        i++;
    }
    this.height = +tmp;
    i++;
    tmp = "";

    this.elems_num = this.width*this.height;

    var j: number = 0;
    var k: number = 0;
    for (j = 0; j < this.height; j++) {
      var tmp_arr: number[] = [];
      for (k = 0; k < this.width; k++) {
        while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0') {
            tmp += hm[i];
            i++;
        }
        tmp_arr.push(+tmp)
        i++;
        tmp = "";
      }
      this.data.push(tmp_arr)
    }
    this.calcMaxHeight();
  }

  calcMaxHeight() {
    if (this.elems_num) {
      this.max_height = this.data[0][0];
      this.data.forEach(arr => arr.forEach(val => {
        if (val > this.max_height)
          this.max_height = val;
      }));
    }
    else
      this.max_height = 0;
  }
}
