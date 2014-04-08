
var reflection = function(name, type) {
  this.name = name;
  this.type = type;
};

reflection.CLASS      = 1;
reflection.INTERFACE  = 2;
reflection.TRAIT      = 3;

reflection.prototype.properties = function(items) {
  return this;  
};
reflection.prototype.methods = function(items) {
  return this;  
};
reflection.prototype.final = function() {
  return this;  
};
reflection.prototype.abstract = function() {
  return this;  
};
reflection.prototype.implements = function(interfaces) {
  return this;  
};
reflection.prototype.extends = function(class) {
  return this;
};
reflection.prototype.getClass = function() {
  if (!this.builder) {
    this.builder = poojs.create(this);
  }
  return this.builder;
};


var accessor = function(value) {
  this.value = value;
};

accessor.PUBLIC = 1;
accessor.PROTECTED = 2;
accessor.PRIVATE = 3;

accessor.prototype.public = function() {
  this.visibility = accessor.PUBLIC;
  return this;
};
accessor.prototype.protected = function() {
  this.visibility = accessor.PROTECTED;
  return this;
};
accessor.prototype.private = function() {
  this.visibility = accessor.PRIVATE;
  return this;
};
accessor.prototype.abstract = function() {
  this.abstract = true;
  return this;
};
accessor.prototype.static = function() {
  this.static = true;
  return this;
};
accessor.prototype.final = function() {
  this.final = true;
  return this;
};

/** PSEUDO IMPL poojs **/
var poojs = {
  create: function(reflection) {
    var constructor = function() {
      // ???
    };
    constructor.prototype.constructor = constructor;
    // instance getter
    constructor.prototype.getClass = function() {
      return reflection
    };
    // static getter
    constructor.getClass = function() {
      return reflection
    };
    return constructor;
  }
};

/** API : **/
module.exports = {
  Class: function(name, decl) {
    var ref = new reflection(name, reflection.CLASS);
    if (decl) {
      if (decl.hasOwnProperty('properties')) ref.properties(decl.properties);
      if (decl.hasOwnProperty('methods')) ref.methods(decl.methods);
    }
    return ref;
  },
  Interface: function(name, functions) {
    var ref = new reflection(name, reflection.INTERFACE);
    if (functions) {
      ref.functions(functions);
    }
    return ref;
  },
  Trait: function(name) {
    return new reflection(name, reflection.TRAIT);
  },
  fn: function(callback) {
    return new accessor(callback);
  },
  prop: function(default) {
    return new accessor(default);
  }
};
