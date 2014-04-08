var $ = require('./jsOOP');

var foo = $.Class('foo')
  .properties({
    foo: $.prop(123).protected().static()
  })
  .methods({
    __construct: $.fn(function() {
      
    }).public(),
    foo: $.fn(function(arg) {
      return this.__self__.foo;
    }).public().final()
  })
.getPrototype();

var bar = $.Class('bar').extends(foo)
  .properties({
    foo: $.prop(321).protected().static()
  })
  .methods({
    __construct: $.fn(function() {
      this.__parent__.__construct();
    }).public().final()
  })
.getPrototype();

var i1 = new foo();
var i2 = new bar();

console.log(i1.foo());