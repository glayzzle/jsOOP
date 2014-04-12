/**
 * Test reflection
 *
 * Build and run test :
 *
 *      sudo node-gyp configure && sudo node-gyp build && node test.js
 */

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

console.log(car);
console.log(car.protectedVar1);