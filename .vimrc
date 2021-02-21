syntax on
set number
filetype detect

call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdtree'
Plug 'jiangmiao/auto-pairs'
call plug#end()

" maintain folds between sessions
autocmd BufWinLeave *.* mkview
autocmd BufWinEnter *.* silent loadview 
highlight Comment ctermfg = green 
set clipboard+=unnamedplus
set mouse=a
set background=dark 
set tabstop=4
set autoindent
set shiftwidth=4
set softtabstop=4
set smarttab
set expandtab
set smartcase
set matchpairs={:},[:],<:>,':',":"
nnoremap <C-y> "+y
vnoremap <C-y> "+y
nnoremap <C-p> "+gP
vnoremap <C-p> "+gP
set backspace=indent,eol,start
set cindent
set showcmd
set autowrite
set autoread


map <F5> :<C-U>!g++ -O2 -DLOCAL -std=c++17 -Wall -Wextra -Dnp -static %:r.cpp -o %:r<CR>
