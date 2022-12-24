import { Component } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-list-item',
  templateUrl: './list-item.component.html',
  styleUrls: ['./list-item.component.css']
})
export class ListItemComponent {
  @Input() name: string='123';
  @Input() id: number | undefined = undefined;
  @Input() isSelected: boolean = false;
  @Output() select = new EventEmitter<listElem>();

  public onClick(name: string, id: number | undefined): void {
    let list_elem: listElem = {name: name, id: id};
    this.select.emit(list_elem);
  }
}

export interface listElem {
  name: string;
  id: number | undefined;
}