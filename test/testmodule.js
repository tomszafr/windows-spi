const spiCaller = require('../index');

const arg = {
  MouseSensitivity: 10,
  MouseSpeed: 2,
  MouseThreshold1: 2,
  MouseThreshold2: 5,
};

const test = async () => {
  const results = {};
  try {
    results.originalSensitivity = await spiCaller.spiGet('SPI_GETMOUSESPEED', 'integer');
    results.originalSettings = await spiCaller.spiGet('SPI_GETMOUSE', 'array');
    results.changeSensMessage = await spiCaller.spiSet('SPI_SETMOUSESPEED', parseInt(arg.MouseSensitivity, 10));
    results.changeSettingsMessage = await spiCaller.spiSet(
      'SPI_SETMOUSE',
      [
        parseInt(arg.MouseThreshold1, 10),
        parseInt(arg.MouseThreshold2, 10),
        parseInt(arg.MouseSpeed, 10)
      ]
    );
    results.changedSensitivity = await spiCaller.spiGet('SPI_GETMOUSESPEED', 'integer');
    results.changedSettings = await spiCaller.spiGet('SPI_GETMOUSE', 'array');
    results.resetSensMessage = await spiCaller.spiSet(
      'SPI_SETMOUSESPEED', parseInt(results.originalSensitivity, 10)
    );
    results.resetSettingsMessage = await spiCaller.spiSet(
      'SPI_SETMOUSE', results.originalSettings
    );
  } catch (error) {
    console.error(error);
  }
  console.log(JSON.stringify(results, null, 4));
};

test();
