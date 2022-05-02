import pygame
import random
import copy
from Point2D import Point
from FlabbyBirb import scale_image2, load_image, make_tuple
pygame.init()

SCREEN_DIMS = {'width': 1024, 'height': 576}
path = 'resources/hugo/sprites/'
game_speed = 5


class Background(pygame.sprite.Sprite):
    def __init__(self, *groups):
        pygame.sprite.Sprite.__init__(self, groups)
        self.image = load_image(path + 'background.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = (0, 0)

    def update(self):
        pass


class Floor:
    def __init__(self, pos):
        self.image = load_image(path + 'base.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = pos


class Pit:
    def __init__(self, pos):
        self.image = load_image(path + 'pit.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = pos


class Ore:
    def __init__(self, pos, type):
        self.image = load_image(path + 'ore' + type + '.png')
        self.rect = self.image.get_rect()
        self.rect.topleft = pos


class Cell(pygame.sprite.Sprite):
    def __init__(self, pos, cell_type, *groups):
        pygame.sprite.Sprite.__init__(self, groups)

        if cell_type == "floor":
            self.cell = Floor(pos)
        elif cell_type == "pit":
            self.cell = Pit(pos)
            self._layer = 3
        elif cell_type == "ore":
            self.cell = Ore(pos, "1")
            self._layer = 4

        self.real_position = Point(pos[0], pos[1])
        self.rect = self.cell.rect
        self.image = self.cell.image
        self.mask = pygame.mask.from_surface(self.image)

        self.width = 2 * 59 - 18

    def update(self):
        self.real_position.x -= game_speed
        self.rect.left = self.real_position.x
        if self.rect.right < 0:
            self.kill()


class Cart(pygame.sprite.Sprite):
    def __init__(self, x, y, *groups):
        super().__init__(*groups)
        # Graphics
        self.image = load_image(path + 'cart.png')
        self.mask = pygame.mask.from_surface(self.image)
        self.rect = self.image.get_rect()
        self.rect.center = (x, y)

        # Movement
        self.movement = 0
        self.gravity = 0.075
        self.is_flying = False
        self.is_dashing = False

    def update(self):
        self.__process_inputs()
        self.__update_movement()

    def __process_inputs(self):
        pass

    def __update_movement(self):

        if self.is_flying is True:
            self.movement += self.gravity

        if self.rect.centery > 525 and self.movement > 0:
            self.movement = 0
            self.is_flying = False
            self.is_dashing = False

        self.rect.centery += self.movement


class Hugo(object):
    def __init__(self):
        # PyGame
        self.screen = pygame.display.set_mode((make_tuple(SCREEN_DIMS)))

        # Events
        self.clock = pygame.time.Clock()
        self.spawn = pygame.USEREVENT
        pygame.time.set_timer(self.spawn, int(random.uniform(900, 1400)))

        # Groups
        self.scenery = pygame.sprite.LayeredUpdates()
        self.player_group = pygame.sprite.GroupSingle()
        self.pit_group = pygame.sprite.Group()
        self.ore_group = pygame.sprite.Group()
        self.cart = Cart(100, 525, self.player_group)

        # Game Variables
        self.game_active = True
        self.running = True
        self.delta_time = 0
        self.time_passed = 0

        # Graphics Initialization
        self.cell_list = []
        self.__init_background()

    def run(self):
        while self.running:
            self.__process_events()
            self.__update()
            self.__draw()

    def __process_events(self):
        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                self.running = False

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w:
                    if self.cart.is_flying is False:
                        self.cart.movement -= 6
                        self.cart.is_flying = True
                        return
                    if self.cart.is_flying:
                        self.cart.movement = 12
                        self.cart.is_dashing = True
                if event.key == pygame.K_ESCAPE:
                    self.running = False

                if event.key == pygame.K_0:
                    global game_speed
                    game_speed = 0.5
                    return
                if event.key == pygame.K_9:

                    game_speed = 5
                    return


    # cells
    # randomness outside of the timer
    # calculate max jump len to know how many pits
    #
    #

    def __update(self):
        self.__update_timings()

        if self.cell_list[-1].rect.right < SCREEN_DIMS['width'] + self.cell_list[-1].width:
            self.__spawn_next()

        self.scenery.update()
        self.pit_group.update()
        self.ore_group.update()
        self.player_group.update()
        self.__check_collisions()

    def __draw(self):
        self.scenery.draw(self.screen)
        self.pit_group.draw(self.screen)
        self.ore_group.draw(self.screen)
        self.player_group.draw(self.screen)

        pygame.display.flip()

    def __update_timings(self):
        self.delta_time = self.clock.tick(120) / 1000
        self.time_passed += self.delta_time / 10
        if self.time_passed > 1:
            global game_speed
            game_speed += 0.5
            self.time_passed = 0

    def __spawn_next(self):
        choice = random.choice([1, 1, 1, 1, 2, 2])
        if choice == 1:
            self.cell_list.append(Cell((self.cell_list[-1].rect.right - 18, 500), "floor", self.scenery))
            if random.choice([1, 1, 1, 1, 1, 2]) == 2:
                self.cell_list.append(Cell((self.cell_list[-2].rect.right - 18, 500), "ore", self.ore_group))
        if choice == 2:
            self.cell_list.append(Cell((self.cell_list[-1].rect.right - 18, 500), "pit", self.pit_group))

    def __init_background(self):
        Background(self.scenery)
        current_pos = 0
        while current_pos < 1.5 * SCREEN_DIMS['width']:
            self.cell_list.append(Cell((current_pos, 500), "floor", self.scenery))
            current_pos += self.cell_list[-1].width

    def __check_collisions(self):

        ore_list = pygame.sprite.spritecollide(self.player_group.sprite, self.pit_group, False, pygame.sprite.collide_mask)
        for pit in ore_list:
            mini_player_rect = copy.deepcopy(self.cart.rect)
            mini_player_rect.width = mini_player_rect.width / 4
            mini_player_rect.right = self.cart.rect.right
            if mini_player_rect.colliderect(pit.rect):
                self.__restart()
                return

        if self.cart.is_dashing is False:
            if pygame.sprite.spritecollide(self.player_group.sprite, self.ore_group, False, pygame.sprite.collide_mask):
                self.__restart()
                return
        else:
            if pygame.sprite.spritecollide(self.player_group.sprite, self.ore_group, True, pygame.sprite.collide_mask):
                self.cart.movement = 0
                self.cart.movement -= 6
                return

    def __restart(self):
        self.scenery.empty()
        self.__init_background()
        global game_speed
        game_speed = 5

        self.pit_group.empty()
        self.ore_group.empty()
        self.player_group.empty()
        self.cart.kill()
        self.cart = Cart(100, 525, self.player_group)