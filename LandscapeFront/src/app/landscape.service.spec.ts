import { TestBed } from '@angular/core/testing';

import { LandscapeService } from './landscape.service';

describe('LandscapeService', () => {
  let service: LandscapeService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(LandscapeService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
