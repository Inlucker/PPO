import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';

/*class Request{
  login: string = '';
  password: string = '';
}*/

@Injectable({
  providedIn: 'root'
})
export class UserService {
  //request: Request = new Request;
  options = { withCredentials: true };

  constructor(private http: HttpClient) { }

  getFreeUsers(): Observable<string[]> {
    return this.http.get<string[]>(this.freeUsersUrl, this.options);
  }

  getUsers(): Observable<string[]> {
    return this.http.get<string[]>(this.usersUrl, this.options);
  }

  login(login: string, password: string): Observable<User> {
    return this.http.post<User>(this.loginUrl, {login, password}, this.options);
  }

  register(login: string, password: string, role: string): Observable<User> {
    return this.http.post<User>(this.registerUrl, {login, password, role}, this.options);
  }

  logout(): Observable<null> {
    return this.http.post<null>(this.logoutUrl, {}, this.options);
  }

  add(user_name: string) {
    return this.http.patch(this.addUrl + "?user_name="+user_name, {}, this.options);
  }

  remove(user_name: string) {
    return this.http.patch(this.removeUrl + "?user_name="+user_name, {}, this.options);
  }

  delete(): Observable<null> {
    return this.http.delete<null>(this.deleteUrl, this.options);
  }
  private freeUsersUrl = environment.baseApiUrl + '/users/free';
  private usersUrl = environment.baseApiUrl + '/users';
  private loginUrl = environment.baseApiUrl + '/login';
  private registerUrl = environment.baseApiUrl + '/register';
  private logoutUrl = environment.baseApiUrl + '/logout';
  private addUrl = environment.baseApiUrl + '/users/moderator/add';
  private removeUrl = environment.baseApiUrl + '/users/moderator/remove';
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