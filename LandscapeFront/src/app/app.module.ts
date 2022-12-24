import { UserService } from './user.service';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LoginWindowComponent } from './login-window/login-window.component';
import { CanvasUserWindowComponent } from './canvas-user-window/canvas-user-window.component';
import { CanvasComponent } from './canvas/canvas.component';
import { TransformsComponent } from './transforms/transforms.component';
import { GroupBoxComponent } from './group-box/group-box.component';
import { ListComponent } from './list/list.component';
import { ModeratorWindowComponent } from './moderator-window/moderator-window.component';
import { ModeratorCanvasWindowComponent } from './moderator-canvas-window/moderator-canvas-window.component';
import { ListItemComponent } from './list-item/list-item.component';

@NgModule({
  declarations: [					
    AppComponent,
    LoginWindowComponent,
    CanvasUserWindowComponent,
    CanvasComponent,
    TransformsComponent,
    GroupBoxComponent,
    ListComponent,
    ModeratorWindowComponent,
    ModeratorCanvasWindowComponent,
    ListItemComponent
   ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
  ],
  providers: [UserService],
  bootstrap: [AppComponent]
})
export class AppModule { }