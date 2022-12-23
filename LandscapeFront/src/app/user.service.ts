import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';

class Request{
  login: string = '';
  password: string = '';
}

@Injectable({
  providedIn: 'root'
})
export class UserService {
  request: Request = new Request;

  constructor(private http: HttpClient) { }

  login(login: string, password: string): Observable<User> {
    /*const httpPostOptions =
    {   
        headers:
            new HttpHeaders (
            {   
                "Content-Type": "application/x-www-form-urlencoded"
            }),
        withCredentials: true,
    };
    return this.http.post<User>(this.loginUrl, "data="+ JSON.stringify({login, password}), httpPostOptions);*/
    return this.http.post<User>(this.loginUrl, {login, password});
    /*this.request.login = login;
    this.request.password = password;
    let jsonRequest = JSON.stringify(this.request)
    return this.http.post<User>(this.loginUrl,
                                "data="+ jsonRequest,
                                { withCredentials: true,
                                  headers: new HttpHeaders({ 'Content-Type': 'application/x-www-form-urlencoded'})
                                })*/
  }

  register(login: string, password: string, role: string): Observable<User> {
    return this.http.post<User>(this.registerUrl, {withCredentials: true, login, password, role});
  }

  logout(): Observable<null> {
    return this.http.post<null>(this.logoutUrl, {});
  }

  delete(): Observable<null> {
    return this.http.delete<null>(this.deleteUrl);
  }

  private loginUrl = environment.baseApiUrl + '/login';
  private logoutUrl = environment.baseApiUrl + '/logout';
  private registerUrl = environment.baseApiUrl + '/register';
  private deleteUrl = environment.baseApiUrl + '/me';
}

export class Status {
  code: number = 0;
  description: string = '';
  message: string = '';
  status: number = 0;
}

export class User {
  id: number = 0;
  login: string = '';
  password: string = '';
  role: string = '';
  moderator_id: number = 0;
}