export class ZBuffer {
  data: number[][] = [];
  width: number = 0;
  height: number = 0;

  setSize(w: number, h: number)
  {
    this.width = w;
    this.height = h;
    for (let i = 0; i < this.height; i++)
    {
      let tmp_arr: number[] = [];
      for (let j = 0; j < this.width; j++)
        tmp_arr.push(Number.MIN_SAFE_INTEGER);
      this.data.push(tmp_arr);
    }
  }
}
