import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { LoginWindowComponent } from './login-window/login-window.component';
import { CanvasUserWindowComponent } from './canvas-user-window/canvas-user-window.component';

const routes: Routes = [
  { path: 'login', component: LoginWindowComponent },
  { path: 'CanvasUserWindow', component: CanvasUserWindowComponent }
  
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
