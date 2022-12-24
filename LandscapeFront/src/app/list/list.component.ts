import { Component } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

import { listElem } from './../list-item/list-item.component';

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.css']
})

export class ListComponent {
  @Input() width: string = '201px';
  @Input() height: string = '281px';
  @Input() list: any[] = [];
  selectedId: number = -1;
  @Output() select = new EventEmitter<listElem>();

  onClick(id: number) {
    this.selectedId = id;
  }

  onSelect(list_elem: listElem) {
    this.select.emit(list_elem);
  }
}