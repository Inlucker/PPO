import { Component } from '@angular/core';
import { Input } from '@angular/core';

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.css']
})
export class ListComponent {
  @Input() width: string = '201px';
  @Input() height: string = '281px';
}
