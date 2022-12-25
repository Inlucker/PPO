import { Params } from './params.service';
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class CanvasService {
  options = { withCredentials: true };
  canvasUrl: string = environment.baseApiUrl + '/landscapes'
  genUrl: string = environment.baseApiUrl + '/generation'
  
  constructor(private http: HttpClient) { }

  generate(p: Params): Observable<Canvas> {
    return this.http.get<Canvas>(this.genUrl + '?size=' + p.size +
      '&range=' + p.range +
      '&smoothing=' + (p.smooth ? 'true' : 'false') +
      '&name=' + p.canvas_name + '&red=' + p.red +
      '&green=' + p.green + '&blue=' + p.blue, this.options);
  }

  getCanvas(id: number): Observable<Canvas> {
    return this.http.get<Canvas>(this.canvasUrl + '/' + id, this.options);
  }

  delete(id: number) {
    return this.http.delete<void>(this.canvasUrl + '/' + id, this.options);
  }

  getCanvasesByUserId(user_id: number): Observable<Canvas[]> {
    return this.http.get<Canvas[]>(this.canvasUrl + '?user_id=' + user_id, this.options);
  }

  postCanvas(canvas: Canvas): Observable<number> {
    return this.http.post<number>(this.canvasUrl, canvas, this.options);
  }

  updateCanvas(canvas: Canvas) {
    return this.http.put<void>(this.canvasUrl, canvas, this.options);
  }
}

export class Canvas {
  id: number = 0;
  user_id: number = 0;
  name: string = '';
  heights_map: string = '';
  heights_map_points: string = '';
  red: number = 0;
  green: number = 0;
  blue: number = 0;
}