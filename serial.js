const portName = '/dev/cu.usbmodem14141'
const Serialport = require('serialport')

const port = new Serialport(portName, {
  baudrate: 9600,
  parser: Serialport.parsers.readline('\n')
});

port.on('data', (data) => {
  // console.log(data.toString())
})

const prompt = require('prompt');
prompt.start()

const move = (err, result) => {
  console.log(result)
  port.write(JSON.stringify(result))
  prompt.get(['stepper1', 'stepper2'], move)
}

prompt.get(['stepper1', 'stepper2'], move)



