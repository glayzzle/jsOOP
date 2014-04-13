/**
 * Test reflection
 *
 * Build and run test :
 *
 *      sudo node-gyp configure && sudo node-gyp build && node test.js
 */

var util = require('util');
var addon = require('./build/Release/addon');
var car = new addon.GlzClass('Car');
car.properties({
    'private' : {
        'privateVar1' : 'privateVar1Value',
        'privateVar2' : 'privateVar2Value'
    },
    'protected': {
        'protectedVar1' : 'protectedVar1Value',
        'protectedVar2' : 'protectedVar2Value'
    },
    'public' : {
        'publicVar1' : 'publicVar1Value',
        'publicVar2' : 'publicVar2Value'
    }
});

console.log("\033[40m\033[1;37mTEST PROTOTYPE\033[0m");
console.log(addon.GlzClass.prototype);

console.log("\033[40m\033[1;37mTEST INSTANCE\033[0m");
console.log(car);


console.log("\033[40m\033[1;37mTEST SET PUBLIC\033[0m");
car.publicVar1 = "publicVar1NewValue";
console.log(car);