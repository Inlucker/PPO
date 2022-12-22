import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CanvasUserWindowComponent } from './canvas-user-window.component';

describe('CanvasUserWindowComponent', () => {
  let component: CanvasUserWindowComponent;
  let fixture: ComponentFixture<CanvasUserWindowComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ CanvasUserWindowComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(CanvasUserWindowComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
