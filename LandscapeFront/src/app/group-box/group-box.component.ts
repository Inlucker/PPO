import { Component } from '@angular/core';
import { Input } from '@angular/core';

@Component({
  selector: 'app-group-box',
  templateUrl: './group-box.component.html',
  styleUrls: ['./group-box.component.css']
})
export class GroupBoxComponent {
  @Input() name: string='';
  @Input() nameAlign: string='';
  @Input() styles: any = {};
}
