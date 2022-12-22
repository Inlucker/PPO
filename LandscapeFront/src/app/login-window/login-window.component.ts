import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { lastValueFrom } from 'rxjs';
import { UserService, Status } from '../user.service';

class LoginForm
{
  constructor(l: string, p: string) {
    this.login = l;
    this.password = p;
   }
  login: string = '';
  password: string = '';
}

@Component({
  selector: 'app-login-window',
  templateUrl: './login-window.component.html',
  styleUrls: ['./login-window.component.css']
})
export class LoginWindowComponent implements OnInit {
  login = 'user1';
  password = '123';
  status: Status = new Status;
  role: string = 'canvas_user';

  constructor(
    private user_service: UserService,
    private router: Router
    ) { }

    ngOnInit(): void {}

    onLogin() {
    let lf: LoginForm = new LoginForm(this.login, this.password);
    let p = lastValueFrom(this.user_service.login(this.login, this.password))
    .then(res => {
      this.status = res;
      if (this.status.description == 'canvas_user')
      this.router.navigate(['/CanvasUserWindow']);});
  }
}