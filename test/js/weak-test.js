/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

const test     = require('tap').test
    , testRoot = require('path').resolve(__dirname, '..')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'weak' });

test('weak', function (t) {
  t.plan(2);

  var weak = bindings;
  t.type(weak.hustle, 'function');

  function f() {
    weak.hustle(function () {}, function (val) {
      t.equal(val, 42);
    });
  };

  f();

  // run weak callback, should dispose
  gc();

  // do not run weak callback
  gc();
});
