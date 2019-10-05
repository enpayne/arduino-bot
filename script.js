window.api = {
  goForward() {
    axios.get('localhost/move?direction=forward');
    console.log('move forward');

  },

  goLeft() {
    console.log('move left');
  },

  goRight() {
    console.log('move right');
  },

  goBack() {
    console.log('move back');
  }
};

document.querySelectorAll('button').forEach(button => {
  button.addEventListener('mousedown', () => {
    button.classList.add('focus');
  });
  button.addEventListener('mouseup', () => {
    button.classList.remove('focus');
  });
});

document.querySelector('#forward').addEventListener('mousedown', window.api.goForward);
document.querySelector('#left').addEventListener('mousedown', window.api.goLeft);
document.querySelector('#right').addEventListener('mousedown', window.api.goRight);
document.querySelector('#back').addEventListener('mousedown', window.api.goBack);
