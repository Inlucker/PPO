import { Component } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-list-item',
  templateUrl: './list-item.component.html',
  styleUrls: ['./list-item.component.css']
})
export class ListItemComponent {
  @Input() name: string='123';
  @Input() isSelected: boolean = false;
  @Output() select = new EventEmitter<string>();

  public onClick(name: string): void {
    this.select.emit(name);
  }
}
