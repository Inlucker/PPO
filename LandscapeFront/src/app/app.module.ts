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

@NgModule({
  declarations: [		
    AppComponent,
    LoginWindowComponent,
    CanvasUserWindowComponent,
      CanvasComponent,
      TransformsComponent
   ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }