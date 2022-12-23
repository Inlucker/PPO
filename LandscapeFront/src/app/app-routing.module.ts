import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { LoginWindowComponent } from './login-window/login-window.component';
import { CanvasUserWindowComponent } from './canvas-user-window/canvas-user-window.component';
import { ModeratorWindowComponent } from './moderator-window/moderator-window.component';
import { ModeratorCanvasWindowComponent } from './moderator-canvas-window/moderator-canvas-window.component';

const routes: Routes = [
  {path: '', redirectTo: '/login', pathMatch: 'full'},
  { path: 'login', component: LoginWindowComponent },
  { path: 'CanvasUserWindow', component: CanvasUserWindowComponent },
  { path: 'ModeratorWindow', component: ModeratorWindowComponent },
  { path: 'ModeratorCanvasWindow', component: ModeratorCanvasWindowComponent },  
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
