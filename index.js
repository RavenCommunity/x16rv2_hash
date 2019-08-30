// Don't export bindings unless there is fs access.
// Intended to disable x16rv2 import in browser where extensions are unavailable.
if (require('fs').accessSync) {
    // console.log('Exporting x16r bindings.');
    module.exports = require('bindings')('nodex16rv2.node');
} else {
    // console.log('Could not export x16rv2 bindings (no fs access).');
}
