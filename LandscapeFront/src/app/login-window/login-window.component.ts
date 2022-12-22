import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { UserService, Status } from '../user.service';


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
    this.user_service.login(this.login, this.password).subscribe(res => this.status = res)
    if (this.status.description == 'canvas_user')
      this.router.navigate(['/CanvasUserWindow']);
  }
}