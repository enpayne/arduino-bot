const ip = '192.168.4.1';

function moveLeft(value) {
  console.log(value);
  fetch(`http://${ip}/left/${value}`);
}

function moveRight(value) {
  console.log(value);
  fetch(`http://${ip}/right/${value}`);
}

document.querySelector('#left').addEventListener('change', (event) => moveLeft(event.target.value));
document.querySelector('#right').addEventListener('change', (event) => moveRight(event.target.value));
