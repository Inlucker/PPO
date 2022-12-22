import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class UserService {

  constructor(private http: HttpClient) { }

  login(login: string, password: string): Observable<Status> {
    return this.http.post<Status>(this.loginUrl, {login, password});
  }
  private loginUrl = environment.baseApiUrl + '/login';
}

export class Status {
  code: number = -1;
  description: string = '';
  message: string = '';
  status: number = -1;
}