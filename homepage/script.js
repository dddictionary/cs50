import anime from 'animejs/lib/anime.es.js'

let welcome = document.querySelector('#welcome')

anime({
    targets: welcome,
    translateX: 250,
    rotate: '1turn',
    backgroundColor: '#FFF',
    duration: 800
  });


