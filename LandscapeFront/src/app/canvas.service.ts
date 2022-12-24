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
  
  constructor(private http: HttpClient) { }

  getCanvas(id: number): Observable<Canvas> {
    return this.http.get<Canvas>(this.canvasUrl + '/' + id, this.options);
  }

  delete(id: number) {
    return this.http.delete<Canvas>(this.canvasUrl + '/' + id, this.options);
  }

  getCanvasesByUserId(user_id: number): Observable<Canvas[]> {
    return this.http.get<Canvas[]>(this.canvasUrl + '?user_id=' + user_id, this.options);
  }

  postCanvas(canvas: Canvas) {
    return this.http.post<Canvas>(this.canvasUrl, canvas, this.options);
  }

  updateCanvas(canvas: Canvas) {
    return this.http.put<Canvas>(this.canvasUrl, canvas, this.options);
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