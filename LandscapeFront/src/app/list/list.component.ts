import { Component } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.css']
})
export class ListComponent {
  @Input() width: string = '201px';
  @Input() height: string = '281px';
  @Input() list: string[] = [];
  selectedId: number = -1;
  @Output() select = new EventEmitter<string>();

  onClick(id: number) {
    this.selectedId = id;
  }

  onSelect(name: string) {
    this.select.emit(name);
  }
}
