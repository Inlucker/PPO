import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { lastValueFrom } from 'rxjs';
import { UserService, User } from '../user.service';

@Component({
  selector: 'app-login-window',
  templateUrl: './login-window.component.html',
  styleUrls: ['./login-window.component.css']
})
export class LoginWindowComponent implements OnInit {
  login = 'user1';
  password = '123';
  user: User = new User;
  role: string = 'canvas_user';

  constructor(
    private user_service: UserService,
    private router: Router
    ) { }

    ngOnInit(): void {}

    onLogin() {
    lastValueFrom(this.user_service.login(this.login, this.password))
                  .then(res => {
                    this.user = res;
                    if (this.user.role == 'canvas_user')
                      this.router.navigate(['/CanvasUserWindow']);
                    else if ((this.user.role == 'moderator'))
                      this.router.navigate(['/ModeratorWindow']);
                  })
                  .catch(e => window.alert(e.message))
  }

  onRegister()
  {
    lastValueFrom(this.user_service.register(this.login, this.password, this.role))
                  .then(res => {
                    this.user = res;
                    if (this.user.role == 'canvas_user')
                      this.router.navigate(['/CanvasUserWindow']);
                    else if ((this.user.role == 'moderator'))
                      this.router.navigate(['/ModeratorWindow']);
                  })
                  .catch(e => window.alert(e.message) /*console.error(e.message)*/)
  }
}