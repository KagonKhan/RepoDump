import pygame
import random
from Point2D import Point
pygame.init()

def scale_image2(image):
    return pygame.transform.scale2x(image)


def load_image(source):
    return scale_image2(pygame.image.load(source).convert_alpha())


def make_tuple(dictionary):
    return [value for key, value in dictionary.items()]


SCREEN_DIMS = {'width': 576, 'height': 1024}
#        self.floor_surf = load_image(self.path + 'base.png')
#        self.floor_pos = Point(0, 900)


# PyGame rects don't accept fractions
class Background(pygame.sprite.Sprite):
    def __init__(self, path, pos, *groups):
        pygame.sprite.Sprite.__init__(self, groups)
        self._layer = 1
        self.image = load_image(path + 'background-day.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = pos
        self.real_position = Point(pos[0], pos[1])

    def update(self):
        self.real_position.x -= 0.2
        if self.rect.right < 0:
            self.real_position.x = SCREEN_DIMS['width']
        self.rect.left = self.real_position.x


class Floor(pygame.sprite.Sprite):
    def __init__(self, path, pos, *groups):
        pygame.sprite.Sprite.__init__(self, groups)
        self._layer = 2
        self.image = load_image(path + 'base.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = pos
        self.real_position = Point(pos[0], pos[1])

    def update(self):
        self.real_position.x -= 5
        if self.rect.right < 0:
            self.real_position.x = SCREEN_DIMS['width']
        self.rect.left = self.real_position.x


class Flabby(object):
    path = 'resources/birb/sprites/'

    def __init__(self):
        # PyGame Initialization
        self.screen = pygame.display.set_mode(make_tuple(SCREEN_DIMS))

        # Event Initialization
        self.clock = pygame.time.Clock()
        self.SPAWNPIPE = pygame.USEREVENT
        pygame.time.set_timer(self.SPAWNPIPE, 1200)

        # Game Variables
        self.game_active = True
        self.running = True
        self.delta_time = 0

        # Groups
        self.all_sprites = pygame.sprite.LayeredUpdates()
        self.player_group = pygame.sprite.GroupSingle()
        self.obstacle_group = pygame.sprite.Group()
        self.bird = self.Bird(self, 100, 512, self.player_group)

        # Graphics Initialization
        Background(self.path, (0, 0), self.all_sprites)
        Background(self.path, (SCREEN_DIMS['width'], 0), self.all_sprites)
        floor_width = Floor(self.path, (0, 900), self.all_sprites).rect.width
        Floor(self.path, (floor_width, 900), self.all_sprites)

    def run(self):
        while self.running:
            self.delta_time = self.clock.tick(120) / 1000
            self.__process_events()
            self.__update()
            self.__draw()

    def __process_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w and self.game_active is False:
                    self.__restart()
                if event.key == pygame.K_ESCAPE:
                    self.running = False
            if event.type == self.SPAWNPIPE and self.game_active is True:
                self.__create_pipes()

    def __update(self):
        self.all_sprites.update()
        self.game_active = self.__check_collision()
        if self.game_active is True:
            self.bird.update()
            if self.bird.rect.bottom > 900:
                self.game_active = False

            self.obstacle_group.update()

    def __draw(self):
        self.all_sprites.draw(self.screen)
        if self.game_active:
            self.player_group.draw(self.screen)
            self.obstacle_group.draw(self.screen)
        pygame.display.flip()

    def __create_pipes(self):
        y = random.choice([400, 600, 800])
        self.Pipe(y, "bot", self.obstacle_group)
        self.Pipe(y, "top", self.obstacle_group)

    def __restart(self):
        self.game_active = True
        self.obstacle_group.empty()
        self.player_group.empty()
        self.bird = self.Bird(self, 100, 512, self.player_group)

#   ===============================================     CLASS     ===============================================
    
    class Bird(pygame.sprite.Sprite):
        def __init__(self, flabby_game, x, y, *groups):
            super().__init__(*groups)
            self.flabby_game = flabby_game

            # Graphics
            path = self.flabby_game.path
            source = (path + 'bluebird-downflap.png', path + '/bluebird-midflap.png', path + 'bluebird-upflap.png')
            self.animation = [load_image(source[0]), load_image(source[1]), load_image(source[2])]
            self.animation_index = 0
            self.surface = self.animation[self.animation_index]
            self.rect = self.surface.get_rect(center=(x, y))
            self.image = self.surface

            # Movement
            self.movement = 0
            self.gravity = 0.25

        def update(self):
            self.__process_inputs()
            self.__update_movement()
            self.__update_sprite()

        def __process_inputs(self):
            keys = pygame.key.get_pressed()
            if keys[pygame.K_w]:
                self.movement = 0
                self.movement -= 10

        def __update_sprite(self):
            self.surface = self.animation[int(self.animation_index)]
            self.rect = self.surface.get_rect(center=(100, self.rect.centery))
            self.image = pygame.transform.rotozoom(self.surface, -self.movement * 3, 1)
            self.animation_index += 50 * self.flabby_game.delta_time
            if self.animation_index >= len(self.animation):
                self.animation_index = 0

        def __update_movement(self):
            self.movement += self.gravity
            self.rect.centery += self.movement
            if self.rect.top < 0:
                self.rect.top = 0
                self.movement = 0


    class Pipe(pygame.sprite.Sprite):
        def __init__(self, y, position, *groups):
            super().__init__(groups)
            self._layer = 3
            self.image = load_image('resources/birb/sprites/pipe-green.png')
            if position == "bot":
                self.rect = self.image.get_rect(midtop=(700, y))
            elif position == "top":
                self.rect = self.image.get_rect(midbottom=(700, y - 300))
                self.image = pygame.transform.flip(self.image, False, True)

        def update(self):
            self.rect.centerx -= 5
            self.__destroy()

        def __destroy(self):
            if self.rect.x < -200:
                self.kill()

    # _______________________________________   GAME FUNCS   _______________________________________

    def __check_collision(self):
        if pygame.sprite.spritecollide(self.player_group.sprite, self.obstacle_group, False):
            return False
        return True
