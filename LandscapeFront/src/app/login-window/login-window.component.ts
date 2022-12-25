import { LandscapeService } from './../landscape.service';
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
  //user: User = new User;
  role: string = 'canvas_user';

  constructor(
    private user_service: UserService,
    private router: Router
    ) {
      let r = localStorage.getItem('role');
      if (r == 'canvas_user')
        router.navigate(['/CanvasUserWindow'])
      if (r == 'moderator') {
        let url = localStorage.getItem('moderator_endpoint');
        if (url)
          this.router.navigate([url]);
        else
          this.router.navigate(['/ModeratorWindow']);
      }

      if (localStorage.getItem('login') != null)
        this.login = localStorage.getItem('login')!
      if (localStorage.getItem('password') != null)
        this.password = localStorage.getItem('password')!
      if (localStorage.getItem('role_comboBox') != null)
        this.role = localStorage.getItem('role_comboBox')!
     }

  ngOnInit() { }

  onLogin() {
    lastValueFrom(this.user_service.login(this.login, this.password))
                  .then(user => {
                    localStorage.setItem('role', user.role);
                    if (user.role == 'canvas_user') {
                      localStorage.setItem('cur_user_id', user.id.toString());
                      LandscapeService.reset();
                      this.router.navigate(['/CanvasUserWindow']);
                    }
                    else if ((user.role == 'moderator'))
                      this.router.navigate(['/ModeratorWindow']);
                  })
                  .catch(e => window.alert(e.message))
  }

  onRegister()
  {
    lastValueFrom(this.user_service.register(this.login, this.password, this.role))
                  .then(user => {
                    localStorage.setItem('role', user.role);
                    if (user.role == 'canvas_user')
                      this.router.navigate(['/CanvasUserWindow']);
                    else if ((user.role == 'moderator'))
                      this.router.navigate(['/ModeratorWindow']);
                  })
                  .catch(e => window.alert(e.message) /*console.error(e.message)*/)
  }

  updateLogin() {
    localStorage.setItem('login', this.login);
  }
  updatePassword() {
    localStorage.setItem('password', this.password);
  }
  updateRole() {
    localStorage.setItem('role_comboBox', this.role);
  }
}