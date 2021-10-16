import pygame
import random

pygame.init()

win_width = 600
win_height = 600
snake_piece_width = 40
score = 0

win = pygame.display.set_mode((win_width, win_height))
pygame.display.set_caption("Snake")
clock = pygame.time.Clock()

bg_color = (201,201,201)
snake_color = (145,29,143)
apple_color = (149,250,122)

def restartGame():
    global run
    global snake_pieces
    global snake_head
    global direction
    global apple
    snake_pieces = [[320,320],[320,360],[320,400]]
    snake_head = [320, 320]
    direction = [0,-1]
    apple =  [320, 160]
    
    i = 0
    while i < 300:
        pygame.time.delay(10)
        i += 1
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                i = 301
                pygame.quit()
                run = False 

def randomApple():
    global apple
    global snake_pieces

    czy_koniec = False
    while not czy_koniec:
        x = random.randint(0,win_width//snake_piece_width - 1)
        y = random.randint(0,win_height//snake_piece_width - 1)
        czy_koniec = True
        for piece in snake_pieces:
            if piece[0] == x * snake_piece_width and piece[1] == y * snake_piece_width:
                czy_koniec = False
        print(czy_koniec)        

    apple = [x * snake_piece_width,y * snake_piece_width]

def redrawGameWindow():
    pygame.draw.rect(win, bg_color, (0,0,win_width,win_height))
    pygame.draw.rect(win, apple_color, (apple[0],apple[1],snake_piece_width,snake_piece_width))
    for piece in snake_pieces:
        pygame.draw.rect(win, snake_color, (piece[0],piece[1],snake_piece_width,snake_piece_width))

    font = pygame.font.SysFont(None, 50)
    img = font.render(str(score), True, (0,0,255))
    win.blit(img, (20, 20))

    pygame.display.update()


snake_head = [320, 320]
snake_pieces = [[320,320],[320,360],[320,400]]
apple =  [320, 160]
run = True
direction = [0,-1]

while run:
    clock.tick(10)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    for i in range(1,len(snake_pieces)):
        if snake_pieces[0][0] == snake_pieces[i][0] and snake_pieces[0][1] == snake_pieces[i][1]:
            restartGame()
            break

    keys = pygame.key.get_pressed()
    if keys[pygame.K_UP]:
        direction = [0,-1]
    elif keys[pygame.K_DOWN]:
        direction = [0,1]
    elif keys[pygame.K_LEFT]:
        direction = [-1,0]
    elif keys[pygame.K_RIGHT]:
        direction = [1,0]

    if apple[0] == snake_pieces[0][0] and apple[1] == snake_pieces[0][1]:
        snake_head_x = snake_piece_width*direction[0] + snake_pieces[0][0]
        snake_head_y = snake_piece_width*direction[1] + snake_pieces[0][1]
        snake_pieces.insert(0,[snake_head_x,snake_head_y])
        score += 1
        randomApple()
    else:
        snake_head_x = snake_piece_width*direction[0] + snake_pieces[0][0]
        snake_head_y = snake_piece_width*direction[1] + snake_pieces[0][1]
        snake_pieces.insert(0,[snake_head_x,snake_head_y])
        snake_pieces.pop(len(snake_pieces)-1)

    if snake_pieces[0][0] < 0 or snake_pieces[0][0] + snake_piece_width > win_width:
        restartGame()
        score = 0
    elif snake_pieces[0][1] < 0 or snake_pieces[0][1] + snake_piece_width > win_height:
        restartGame()
        score = 0

    redrawGameWindow()

pygame.quit()
