var argv = require('yargs')
  .usage('Usage: beehive -s [serialPort] -d [debug] -p [serverPort] -u [username] -P [password]')
  .help('help')
  .alias('help', 'h')
  .option('debug', {
        alias: 'd',
        demand: false,
        describe: 'Debug Mode (aka Verbose mode).',
        type: 'boolean'
    })
  .default('debug', undefined)
  .option('serialport', {
        alias: 's',
        demand: false,
        describe: 'Arduino Serial Port.',
        type: 'string'
    })
  .option('username', {
        alias: 'u',
        demand: false,
        describe: 'Username for Web Interface and API',
        type: 'string'
    })
  .option('password', {
        alias: 'P',
        demand: false,
        describe: 'Password for Web Interface and API',
        type: 'string'
    })
  .implies('username', 'password')
  .implies('password', 'username')
  .option('port', {
        alias: 'p',
        demand: false,
        describe: 'HTTP Server Port.',
        type: 'number'
    })
  .example('beehive -d false', 'Choose to enable or not Debug Mode')
  .example('beehive -s COM4', 'Start the system using arduino on the specified serial port')
  .example('beehive -u username -P password', 'Start the system setting custom username and password')
  .example('beehive -p 8080', 'Start the system server on the specified port')
  .epilogue('@Author: Davide Neri - github.com/dido18')
  .argv;

console.log(argv);

module.exports = argv;
